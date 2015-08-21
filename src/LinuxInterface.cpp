/******************************************************************************/
/*                                                                            */
/*  LinuxInterface.cpp                                                        */
/*                                                                            */
/*  Copyright (C) 2015, Joseph Andrew Staedelin IV                            */
/*                                                                            */
/*  This file is part of the FastGdk project.                                 */
/*                                                                            */
/*  The FastGdk is free software: you can redistribute it and/or modify       */
/*  it under the terms of the GNU Lesser General Public License as published  */
/*  by the Free Software Foundation, either version 3 of the License, or      */
/*  (at your option) any later version.                                       */
/*                                                                            */
/*  The FastGdk is distributed in the hope that it will be useful,            */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/*  GNU Lesser General Public License for more details.                       */
/*                                                                            */
/*  You should have received a copy of the GNU Lesser General Public License  */
/*  along with the FastGdk.  If not, see <http://www.gnu.org/licenses/>.      */
/*                                                                            */
/******************************************************************************/

#if defined(FastOSLinux)
#	include <unistd.h>
#	include <fcntl.h>
#	include <libudev.h>
#	include <linux/joystick.h>
#	include <string.h>
#endif

#include "LinuxInterface.hpp"

#include "Undefs.hpp"

namespace Fast
{

#if defined(FastOSLinux)

	Array<GamepadDeviceInfo> LinuxGetAttachedJoysticks() {
		Array<GamepadDeviceInfo> deviceInfoArray;
		udev *udev_context;
		udev_enumerate *enumerate;
		udev_list_entry *devices, *dev_list_entry;
		udev_device *dev;
		udev_context = udev_new();
		if (!udev_context) {
			// TODO: Throw error
			return deviceInfoArray;
		}
		enumerate = udev_enumerate_new(udev_context);
		udev_enumerate_add_match_subsystem(enumerate, "input");
		udev_enumerate_scan_devices(enumerate);
		devices = udev_enumerate_get_list_entry(enumerate);
		udev_list_entry_foreach(dev_list_entry, devices) {
			const char *path = NULL, *devnode = NULL;
			path = udev_list_entry_get_name(dev_list_entry);
			dev = udev_device_new_from_syspath(udev_context, path);
			devnode = udev_device_get_devnode(dev);
			dev = udev_device_get_parent_with_subsystem_devtype(
				dev, "usb", "usb_device");
			if (devnode && dev) {
				if (strstr(devnode, "js")) {
					GamepadDeviceInfo deviceInfo;
					deviceInfo.mProductName =
						udev_device_get_sysattr_value(dev, "product");
					deviceInfo.mManufacturer =
						udev_device_get_sysattr_value(dev, "manufacturer");
					deviceInfo.mGuid =
						String(udev_device_get_sysattr_value(dev, "product")) +
						String(udev_device_get_sysattr_value(dev, "idVendor")) +
						String(udev_device_get_sysattr_value(dev, "serial"));
					deviceInfo.mDeviceHandle =
						open(devnode, O_RDONLY | O_NONBLOCK);
					deviceInfoArray.Append(deviceInfo);
				}
			}
			udev_device_unref(dev);
		}
		udev_enumerate_unref(enumerate);
		udev_unref(udev_context);
		return deviceInfoArray;
	}

	GamepadCapabilities LinuxJoystickGetCapabilities(
		JoystickDeviceHandle handle)
	{
		GamepadCapabilities gc;
		char numButtons = 0, numAxes = 0;
		ioctl(handle, JSIOCGBUTTONS, &numButtons);
		ioctl(handle, JSIOCGAXES, &numAxes);
		gc.mNumAxes = (Int)numAxes;
		gc.mNumDirectionalPads = 0; // Dpads/Hats/POVs are just buttons in Linux
		gc.mNumRegularButtons = (Int)numButtons;
		return gc;
	}

	struct LinuxJoystickEvent
	{
		UInt	mTime;
		Short	mValue;
		UByte	mType;
		UByte	mNumber;
	};

	Gamepad LinuxJoystickPoll(const Gamepad &oldGamepad) {
		Gamepad newGamepad = oldGamepad;
		LinuxJoystickEvent lje;
		Int bytesRead = 0;
		do {
			bytesRead = read(newGamepad.GetDeviceInfo().mHandle,
				&lje, sizeof(LinuxJoystickEvent));
			if (0 < bytesRead) {
				switch (lje.mType & ~JS_EVENT_INIT) {
				case JS_EVENT_AXIS: {
						switch (lje.mNumber % 3) {
						case 0:
							newGamepad.SetStickXAxis(
								lje.mNumber / 3, lje.mValue);
							break;
						case 1:
							newGamepad.SetStickYAxis(
								lje.mNumber / 3, lje.mValue);
							break;
						case 2:
							newGamepad.SetStickOtherAxis(
								lje.mNumber / 3, lje.mValue);
							break;
						default:
							break;
						}
						break;
					}
				case JS_EVENT_BUTTON:
					lje.mValue ? newGamepad.PressButton(lje.mNumber) :
						newGamepad.ReleaseButton(lje.mNumber);
					break;
				default:
					// TODO: Error
					break;
				}
			}
		} while (0 < bytesRead);
		return newGamepad;
	}

	void LinuxJoystickClose(JoystickDeviceHandle handle) {
		close(handle);
	}

#endif

}