//
//  opObj.hpp
//  edit
//
//  Created by Le Wang on 5/8/19.
//  Copyright © 2019 Le. All rights reserved.
//

#ifndef opObj_hpp
#define opObj_hpp

#include <iostream>
#include <vector>

using namespace std;

class opObj{
public:
    string opName;
    vector<unsigned long> numParam;
    vector<string> strParam;
    
    opObj();
    opObj(string name);
};

#endif /* opObj_hpp */
