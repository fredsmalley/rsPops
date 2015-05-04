//
//  rsPops.cpp
//  rsPops
//
//  Created by Fred Smalley on 5/4/15.
//  Copyright (c) 2015 Song Lab. All rights reserved.
//
#include "rsPops.h"

int main(int argc, const char * argv[]) {
	
	vector<uint_fast16_t> r;
	vector< vector < uint_fast16_t > > t;
	
	r.push_back(1);
	r.push_back(2);
	t.push_back(r);
	r.clear();
	r.push_back(3);
	r.push_back(4);
	t.push_back(r);
	r.clear();
	r.push_back(5);
	r.push_back(6);
	t.push_back(r);
	
	string rs = "rs123456";
	string pop = "ALL";
	float p = 0.01;
	float pn = 0.001;
	rsInfo rI = rsInfo (rs, p, pn, t, pop);
	
	cout << rI.toString() << endl;
	
    return 0;
}
