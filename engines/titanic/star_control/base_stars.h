/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef TITANIC_BASE_STARS_H
#define TITANIC_BASE_STARS_H

#include "titanic/support/simple_file.h"
#include "titanic/star_control/frange.h"
#include "titanic/star_control/star_closeup.h"
#include "titanic/star_control/surface_area.h"

namespace Titanic {

enum StarMode { MODE_STARFIELD = 0, MODE_PHOTO = 1 };

class CStarCamera;

struct CBaseStarEntry {
	byte _red;
	byte _green;
	byte _blue;
	byte _thickness;
	double _value;
	FVector _position;
	uint _data[5];

	CBaseStarEntry();

	/**
	 * Loads the data for a star
	 */
	void load(Common::SeekableReadStream &s);

	bool operator==(const CBaseStarEntry &s) const;
};

struct CStarPosition : public Common::Point {
	int _index1;
	int _index2;
	CStarPosition() : _index1(0), _index2(0) {}

	bool operator==(const CStarPosition &sp) const {
		return x == sp.x && y == sp.y && _index1 == sp._index1 && _index2 == sp._index2;
	}
};

/**
 * Base class for views that draw a set of stars in simulated 3D space
 */
class CBaseStars {
private:
	void draw1(CSurfaceArea *surfaceArea, CStarCamera *camera, CStarCloseup *closeup);
	void draw2(CSurfaceArea *surfaceArea, CStarCamera *camera, CStarCloseup *closeup);
	void draw3(CSurfaceArea *surfaceArea, CStarCamera *camera, CStarCloseup *closeup);
	void draw4(CSurfaceArea *surfaceArea, CStarCamera *camera, CStarCloseup *closeup);
protected:
	FRange _minMax;
	double _minVal;
	double _maxVal;
	double _range;
	double _value1, _value2;
	double _value3, _value4;
protected:
	/**
	 * Load entry data from a passed stream
	 */
	void loadData(Common::SeekableReadStream &s);

	/**
	 * Load entry data from a specified resource
	 */
	void loadData(const CString &resName);

	/**
	 * Reset the data for an entry
	 */
	void resetEntry(CBaseStarEntry &entry);
public:
	Common::Array<CBaseStarEntry> _data;
public:
	CBaseStars();
	virtual ~CBaseStars() {}

	/**
	 * Draw the item
	 */
	virtual void draw(CSurfaceArea *surfaceArea, CStarCamera *camera, CStarCloseup *closeup);

	virtual bool loadYale(int v1) { return true; }

	/**
	 * Selects a star
	 */
	virtual bool selectStar(CSurfaceArea *surfaceArea, CStarCamera *camera,
		const Common::Point &pt, void *handler = nullptr) { return false; }

	/**
	 * Adds a new star, or removes one if already present at the given co-ordinates
	 */
	virtual bool addStar(const CBaseStarEntry *entry) { return false; }

	virtual bool loadStar() { return false; }

	/**
	 * Load the item's data
	 */
	virtual void load(SimpleFile *file) {}

	/**
	 * Save the item's data
	 */
	virtual void save(SimpleFile *file, int indent) {}

	/**
	 * Clear allocated data
	 */
	void clear();

	void initialize();

	int size() const { return _data.size(); }

	/**
	 * Get a pointer to a data entry
	 */
	const CBaseStarEntry *getDataPtr(int index) const;

	/**
	 * Checks for the presence of a star at a given position on the
	 * screen given the specified camera view, and returns it's index
	 */
	int findStar(CSurfaceArea *surfaceArea, CStarCamera *camera,
		const Common::Point &pt);

	int baseFn2(CSurfaceArea *surfaceArea, CStarCamera *camera);
};

class CStarVector {
private:
	CStarCamera *_owner;
	FVector _vector;
public:
	CStarVector(CStarCamera *owner, const FVector &v) : _owner(owner), _vector(v) {}

	/**
	 * Applies the saved vector
	 */
	void apply();
};

} // End of namespace Titanic

#endif /* TITANIC_BASE_STARS_H */
