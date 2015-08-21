/******************************************************************************/
/*                                                                            */
/*  SpriteData.hpp                                                            */
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

#ifndef FastSpriteDataHppIncluded
#define FastSpriteDataHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetData.hpp>
#include <Fast/Array.hpp>
#include <Fast/String.hpp>
#include <Fast/SpriteCollisionModel.hpp>
#include <Fast/SpriteFrameConfig.hpp>
#include <Fast/SpriteAction.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/Version.hpp>

namespace Fast
{
	class StreamReader;

	class FastApi SpriteData : public AssetData
	{
	private:
		Array<String>				mTexture2DNames;
		Array<String>				mSpriteSheetNames;
		Array<SpriteCollisionModel>	mCollisionModels;
		Array<SpriteFrameConfig>	mFrameConfigs;
		Array<SpriteAction>			mActions;
	public:
		// (Con/De)structors
		SpriteData();
		SpriteData(const SpriteData &that);
		SpriteData(const String &fileName);
		SpriteData(StreamReader *streamReader);
		~SpriteData();
		// Allocators
		ErrorType	Load(const String &fileName);
		ErrorType	Load(StreamReader *streamReader);
		void		Unload();
		// Modify functions
		void	AddTexture2DAndSpriteSheetNames(const String &texture2DName,
					const String &spriteSheetName);
		void	InsertTexture2DAndSpriteSheetNames(const String &texture2DName,
					const String &spriteSheetName, Int index);
		void	ReplaceTexture2DAndSpriteSheetNames(const String &texture2DName,
					const String &spriteSheetName, Int index);
		void	EraseTexture2DAndSpriteSheetNames(Int index);
		void	ClearTexture2DAndSpriteSheetNames();
		void	AddCollisionModel(const SpriteCollisionModel &collisionModel);
		void	InsertCollisionModel(const SpriteCollisionModel &collisionModel,
					Int index);
		void	ReplaceCollisionModel(
					const SpriteCollisionModel &collisionModel, Int index);
		void	EraseCollisionModel(Int index);
		void	ClearCollisionModels();
		void	AddFrameConfig(const SpriteFrameConfig &frameConfig);
		void	InsertFrameConfig(const SpriteFrameConfig &frameConfig,
					Int index);
		void	ReplaceFrameConfig(const SpriteFrameConfig &frameConfig,
					Int index);
		void	EraseFrameConfig(Int index);
		void	ClearFrameConfigs();
		void	AddAction(const SpriteAction &action);
		void	InsertAction(const SpriteAction &action, Int index);
		void	ReplaceAction(const SpriteAction &action, Int index);
		void	EraseAction(Int index);
		void	ClearActions();
		// Get functions
		Int							GetNumTexture2DAndSpriteSheetNames() const;
		const String&				GetTexture2DName(Int index) const;
		Int							GetTexture2DNameIndex(
										const String &name) const;
		const String&				GetSpriteSheetName(Int index) const;
		Int							GetSpriteSheetNameIndex(
										const String &name) const;
		Int							GetNumCollisionModels() const;
		SpriteCollisionModel*		GetCollisionModel(Int index);
		const SpriteCollisionModel&	GetCollisionModel(Int index) const;
		Int							GetCollisionModelIndex(
										const String &name) const;
		Int							GetNumFrameConfigs() const;
		SpriteFrameConfig*			GetFrameConfig(Int index);
		const SpriteFrameConfig&	GetFrameConfig(Int index) const;
		Int							GetFrameConfigIndex(
										const String &name) const;
		Int							GetNumActions() const;
		SpriteAction*				GetAction(Int index);
		const SpriteAction&			GetAction(Int index) const;
		Int							GetActionIndex(const String &name) const;
		// Misc
		ErrorType	SaveAs(const String &fileName,
						const Version &version = Version(0, 1));
		// Operators
		SpriteData&	operator= (const SpriteData &that);
		Bool		operator==(const SpriteData &that) const;
		Bool		operator!=(const SpriteData &that) const;
	};
}

#endif // FastSpriteDataHppIncluded
