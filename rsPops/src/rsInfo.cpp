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

/*!   @fn       rsInfo (const rsInfo& rs)
 *    @brief    Copy constructor
 *
 *    @param    rs An rsInfo object to be copied
 */
rsInfo::rsInfo (const rsInfo& rs) {
	rsID = rs.rsID;
	pValue = rs.pValue;
	p_nValue = rs.p_nValue;
	
	for (map<string, table>::const_iterator itr = rs.tables.begin (); itr != rs.tables.end (); ++itr) {
		tables.insert (make_pair (itr->first, itr->second));
	}
}

/*!   @fn       rsInfo ()
 *    @brief    Default constructor
 */
rsInfo::rsInfo () {
	rsID = "";
	pValue = -1.0;
	p_nValue = -1.0;
}



/*!   @fn       void setPValue (const float& p)
 *    @brief    set GLN p-value
 *
 *    @param    p A float with the new p-value value
 */
void rsInfo::setPValue (const float& p) {	pValue = p;	}

/*!   @fn       void setP_nValue (const float& p)
 *    @brief    set GLN p_n-value
 *
 *    @param    p A float with the new p_n-value value
 */
void rsInfo::setP_nValue (const float& p ) {	p_nValue = p;	}


/*!   @fn       void addPopulation (const string& pop, const pair<float, float>& p, const vector<uint_fast16_t>& v)
 *    @brief    Add information for new Population
 *
 *    @param    pop A string holding the name of the new population
 *
 *
 *    This method adds a new table to this rsID.
 */
void rsInfo::addPopulation (const string& pop, const pair<float, float>& p, const vector<uint_fast16_t>& v) {
	vector< vector<uint_fast16_t> > t;
	vector<uint_fast16_t> r;
	uint_fast16_t max = (v.size () < tables.begin ()->second.table.size ()) ? v.size () : tables.begin ()->second.table.size ();
	for (uint_fast16_t i = 0; i < max; ++i) {
		r.push_back(tables.begin ()->second.table[i][0]);
		r.push_back(v[i]);
		t.push_back(r);
		r.clear();
	}

	tables.insert (make_pair (pop, table{t, p.first, p.second}));
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
	stringstream _ret;
	_ret << scientific;
	_ret.precision(3);
	
	_ret << rsID << ":" << endl;
	
	if (pValue > 0.0 || p_nValue > 0.0) {
		_ret << "GLN";
		if (pValue > 0.0)
			_ret << "\tp-value = " << pValue;
		if (p_nValue > 0.0)
			_ret << "\tp_n-value = " << p_nValue;
	
		_ret << endl;
	}
	
	for (map<string, table>::const_iterator itr = tables.begin (); itr != tables.end (); ++itr) {
		_ret << itr->first << endl << "   \tCR\tN\n";
		for (vector< vector< uint_fast16_t > >::const_iterator i = itr->second.table.begin (); i != itr->second.table.end (); ++i) {
			if (i == itr->second.table.begin ())
				_ret << "SNP";
			else if (i == ++(itr->second.table.begin ()))
				_ret << "REF";
			else
				_ret << " ~ ";
			for (vector< uint_fast16_t >::const_iterator j = i->begin (); j != i->end (); ++j) {
				_ret << "\t" << *j;
			}
			_ret << endl;
		}
		
		_ret << "p-value = " << itr->second.pValue << "\tp_n-value = " << itr->second.p_nValue << endl;
	}
	
	return _ret.str ();
}
