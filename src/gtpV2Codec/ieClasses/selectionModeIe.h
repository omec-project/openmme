/*
* Copyright (c) 2019 Infosys Limited
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef SELECTIONMODEIE_H_
#define SELECTIONMODEIE_H_

#include "manual/gtpV2Ie.h"



class SelectionModeIe: public GtpV2Ie {
public:
    SelectionModeIe();
    virtual ~SelectionModeIe();

    bool encodeSelectionModeIe(MsgBuffer &buffer,
                 SelectionModeIeData const &data);
    bool decodeSelectionModeIe(MsgBuffer &buffer,
                 SelectionModeIeData &data, Uint16 length);
    void displaySelectionModeIe_v(SelectionModeIeData const &data,
                 Debug &stream);
};

#endif /* SELECTIONMODEIE_H_ */