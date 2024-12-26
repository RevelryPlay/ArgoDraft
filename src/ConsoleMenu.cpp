#include "../include/ConsoleMenu.hpp"

namespace ArgoDraft {
	// Get all actions and their aliases
	void Menu::GetActions() {
        for ( auto const &action : actions ) {
          if ( action.second.isAlias ) {
          	continue;
          }
            
            std::cout << action.first << " - " << action.second.Description << std::endl;
            
            if ( action.second.Aliases.empty() ) {
                continue;
            }
            
            std::cout << "Aliases:" << std::endl;
            for ( auto const &alias : action.second.Aliases ) {
                std::cout << " - " << alias;
            }
            
            std::cout << std::endl << std::endl;
        }
    }
    
    // Initialize the menu
    void Menu::Init( const std::string &menu_path ) {
    	const std::string full_path = menu_path + this->Name;
    	std::string input;

    	while ( true ) {
        	std::cout << full_path + "> ";
        	std::cin >> input;
        	if ( this->actions.contains( input ) ) {
            	actions[ input ].Action();
        	} else if ( this->submenus.contains( input ) ) {
            	submenus[ input ].Init( full_path + "/" );
        	} else if ( input == "back" ) {
            	return;
        	} else if ( input == "exit" ) {
            	exit( 0 );
        	} else if ( input == "info" ) {
            	std::string name;
            	std::cin >> name;

            	if ( this->submenus.contains( name ) ) {
               		std::cout << this->submenus[ name ].Description << '\n';
            	} else if ( this->actions.contains( name ) ) {
                	std::cout << this->actions[ name ].Description << '\n';
            	} else {
                	std::cout << "unrecognized name: " << name << '\n';
            	}
        	} else if ( input == "help" ) {
            	std::cout << "back: return to the previous menu\n";
            	std::cout << " exit: exit the program\n";
            	std::cout << " info <name>: get the description of a submenu or action\n";
            	std::cout << " help: show this help message\n";
            	std::cout << " ls: list the submenus and actions for the current menu\n";

            	std::cout << '\n';

            	GetActions();
        	} else if ( input == "ls" ) {
            	GetActions();

            	if ( this->submenus.empty() && this->actions.empty() ) {
                	std::cout << "This menu has no submenus or actions\n";
            	}
        	} else {
            	std::cout << "unrecognized name: " << input << '\n';
        	}
    	}
    }
    
    // Add a submenu
    void Menu::addSubmenu( Menu const &m ) {
        submenus[ m.Name ] = m;
    }
    
    // Add an action
    void Menu::addItemAction( MenuItem const &m ) {
        actions[ m.Name ] = m;
        
        for ( auto const &alias : m.Aliases ) {
          	auto aliasAction = m;
            aliasAction.isAlias = true;
            
            actions[ alias ] = aliasAction;
        }
    }

}
