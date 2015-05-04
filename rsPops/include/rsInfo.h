//
//  rsInfo.h
//  rsPops
//
//  Created by Fred Smalley on 5/4/15.
//  Copyright (c) 2015 Song Lab. All rights reserved.
//

#ifndef __rsPops__rsInfo__
#define __rsPops__rsInfo__

#include <string>
#include <vector>
#include <map>
#include <cstdint>

using std::string;
using std::vector;
using std::map;
using std::make_pair;
using std::to_string;

struct table {
	vector< vector< uint_fast16_t > > table;
	float pValue;
	float p_nValue;
};

class rsInfo {
private:
	string rsID;
	float pValue = -1.0;
	float p_nValue = -1.0;
	map<string, table> tables;

public:
	rsInfo (string&, float&, float&, vector< vector< uint_fast16_t > >&, string&);
	rsInfo (const rsInfo&);
	rsInfo ();
	
	void setPValue (const float&);
	void setP_nValue (const float&);
	void setCancerColumn (const uint_fast16_t&, const uint_fast16_t&);
	void addPopulation (const string&, const float&, const float&, const uint_fast16_t&, const uint_fast16_t&);
	
	const float getPValue () const;
	const float getP_nValue () const;
	const bool getTable (vector< vector< uint_fast16_t > >&, const string&) const;
	const string toString () const;
};

#endif /* defined(__rsPops__rsInfo__) */
