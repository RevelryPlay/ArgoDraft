#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <ranges>
#include <map>
#include <string>


namespace ArgoDraft {
    struct MenuItem {
        std::string Name;
        std::string Description;
        void ( *Action )();
        
        std::vector< std::string > Aliases = {};
        bool isAlias = false;
    };

    class Menu {
      public:
        std::map< std::string, Menu > submenus;
        std::map< std::string, MenuItem > actions;
        
        std::string Name;
        std::string Description;

        Menu() = default;
        Menu( std::string name, std::string desc ) : Name( std::move( name ) ), Description( std::move( desc ) ) {}

        void AddMenu( Menu const &m ) { addSubmenu( m ); }
        void AddAction( MenuItem const &m ) { addItemAction( m ); }
        
        void GetActions();
        void Init( const std::string & );
        
        private:
          void addSubmenu( Menu const &m );
          void addItemAction( MenuItem const &m );
    };

    class MainMenu : public Menu {
      public:
        using Menu::Menu;
        void Init() { this->Menu::Init( "" ); }
    };

}
