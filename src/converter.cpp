/*  BOSS

    A plugin load order optimiser for games that use the esp/esm plugin system.

    Copyright (C) 2013    WrinklyNinja

    This file is part of BOSS.

    BOSS is free software: you can redistribute
    it and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    BOSS is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BOSS.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#include "backend/legacy-parser.h"
#include "backend/generators.h"
#include "backend/streams.h"
#include "backend/metadata.h"

using namespace std;

int main(int argc, char * argv[]) {
    fs::path v2masterlist("../../BOSS/data/boss-skyrim/masterlist.txt");
    list<boss::Plugin> test_plugins;
    list<boss::Message> globalMessages;
    Loadv2Masterlist(v2masterlist, test_plugins, globalMessages);

    YAML::Emitter yout;
    yout.SetIndent(2);
    yout << YAML::BeginMap
         << YAML::Key << "globals" << YAML::Value << globalMessages
         << YAML::Key << "plugins" << YAML::Value << test_plugins
         << YAML::EndMap;

    boss::ofstream out(_game.MasterlistPath());
    out << yout.c_str();
    out.close();

    return 0;
}