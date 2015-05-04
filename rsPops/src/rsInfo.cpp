//
//  rsInfo.cpp
//  rsPops
//
//  Created by Fred Smalley on 5/4/15.
//  Copyright (c) 2015 Song Lab. All rights reserved.
//

#include "rsInfo.h"

/*!   @fn       rsInfo (string& r, float& p, float& pn, vector< vector< uint_fast16_t > >& t, string& pop)
 *    @brief    Basic constructor for rsInfo class
 *
 *		@param[in]	r	The name of the rsID
 *    @param[in]   p	The p-value for the table
 *		@param[in]	pn	The p_n-value for the table
 *
 *    This constructor sets up the values for the rsID and makes the first table
 */
rsInfo::rsInfo (string& r, float& p, float& pn, vector< vector< uint_fast16_t > >& t, string& pop) {
	rsID = r;
	tables.insert (make_pair (pop, (table){t, p, pn}));
}

/*!   @fn       const float getPValue () const
 *    @brief    get trj p-value
 *
 *    @return   A float with the GLN calculated p-value
 *
 */
const float rsInfo::getPValue () const {	return pValue;	}

/*!   @fn       const float getP_nValue () const
 *    @brief    get trj p_n-value
 *
 *    @return   A float with the GLN calculated p-value
 */
const float rsInfo::getP_nValue() const {	return p_nValue;	}

/*!   @fn       const bool getTable (vector< vector< uint_fast16_t > >& t, const string& pop) const
 *    @brief    get the table from a population
 *
 *    @param[in,out] ret	A table to be filled
 *		@param[in]		pop	A string holding the name of the population
 *
 *    This function fills a table with values from a population specific table and returns if the
 *		table existed.
 */
const bool rsInfo::getTable (vector< vector< uint_fast16_t > >& ret, const string& pop) const {
	map<string, table>::const_iterator itr = tables.find(pop);
	if (itr != tables.end ()) {
		const vector< vector< uint_fast16_t > >& table = itr->second.table;
		vector< uint_fast16_t > row;
		for (vector< vector< uint_fast16_t > >::const_iterator i = table.begin (); i != table.end (); ++i) {
			for (vector< uint_fast16_t >::const_iterator j = i->begin (); j != i->end (); ++j)
				row.push_back (*j);
			ret.push_back (row);
			row.clear ();
		}
		
		return true;
	} else
		return false;
}

/*!   @fn       const string toString () const
 *    @brief    toString method
 *
 *    @return   A string holding the info for rsInfo neatly
 *
 *    This is a simple toString method which simply writes all the information in the object neatly
 */
const string rsInfo::toString () const {
	string ret = rsID + ":\n";
	
	if (pValue > 0.0 || p_nValue > 0.0)
		ret += "GLN";
	if (pValue > 0.0)
		ret += "\tp-value = " + to_string (pValue);
	if (p_nValue > 0.0)
		ret += "\tp_n-value = " + to_string (p_nValue);
	
	ret += "\n";
	
	for (map<string, table>::const_iterator itr = tables.begin (); itr != tables.end (); ++itr) {
		ret += itr->first + "\tCR\tN\n";
		for (vector< vector< uint_fast16_t > >::const_iterator i = itr->second.table.begin (); i != itr->second.table.end (); ++i) {
			if (i == itr->second.table.begin ())
				ret += "SNP";
			else if (i == ++(itr->second.table.begin ()))
				ret += "REF";
			else
				ret += " ~ ";
			for (vector< uint_fast16_t >::const_iterator j = i->begin (); j != i->end (); ++j) {
				ret += "\t" + to_string (*j);
			}
			ret += "\n";
		}
		
		ret += "p-value = " + to_string (itr->second.pValue) + "\tp_n-value = " + to_string (itr->second.p_nValue) + "\n";
	}
	
	return ret;
}
