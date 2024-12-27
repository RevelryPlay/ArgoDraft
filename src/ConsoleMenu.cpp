#include "../include/ConsoleMenu.hpp"

namespace ArgoDraft {
    void Menu::GetSubmenus( ) {
        std::cout << "Submenus:" << std::endl;

        if ( submenus.empty( ) ) {
            std::cout << "This menu has no submenus" << std::endl;
            return;
        }

        for ( auto const &submenu : submenus ) {
            std::cout << submenu.first << " - " << submenu.second.Description << std::endl;
        }

        std::cout << std::endl << std::endl;
    }

    // Get all actions and their aliases
    void Menu::GetActions( ) {
        std::cout << "Actions:" << std::endl;

        if ( actions.empty( ) ) {
            std::cout << "This menu has no additional actions" << std::endl;
            return;
        }

        for ( auto const &action : actions ) {
            if ( action.second.isAlias ) {
                continue;
            }

            std::cout << action.first << " - " << action.second.Description << std::endl;

            if ( action.second.Aliases.empty( ) ) {
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
        std::string       input;

        while ( true ) {
            std::cout << full_path + "> ";
            std::cin >> input;

            if ( !isValidCommand( input ) ) {
                std::cout << "Invalid command: " << input << std::endl;
                continue;
            }

            // handle built-in commands
            bool isBuiltin = std::ranges::find( builtInCommands, input ) != builtInCommands.end( );
            if ( isBuiltin ) {
                if ( input == "ls" ) {
                    if ( this->submenus.empty( ) && this->actions.empty( ) ) {
                        std::cout << "This menu has no submenus or actions" << std::endl;
                        continue;
                    }

                    GetSubmenus( );
                    GetActions( );

                } else if ( input == "back" ) {
                    return;
                } else if ( input == "exit" ) {
                    exit( 0 );
                } else if ( input == "info" ) {
                    std::string name;
                    std::cin >> name;

                    if ( this->submenus.contains( name ) ) {
                        std::cout << this->submenus[name].Description << std::endl;
                    } else if ( this->actions.contains( name ) ) {
                        std::cout << this->actions[name].Description << std::endl;
                    }
                } else if ( input == "help" ) {
                    std::cout << "back: return to the previous menu" << std::endl;
                    std::cout << " exit: exit the program" << std::endl;
                    std::cout << " info <name>: get the description of a submenu or action" << std::endl;
                    std::cout << " help: show this help message" << std::endl;
                    std::cout << " ls: list the submenus and actions for the current menu" << std::endl;

                    std::cout << std::endl;

                    if ( this->submenus.empty( ) && this->actions.empty( ) ) {
                        std::cout << "This menu has no submenus or actions" << std::endl;
                        continue;
                    }

                    GetSubmenus( );
                    GetActions( );
                }

                continue;
            }

            // handle actions and submenus
            if ( this->actions.contains( input ) ) {
                actions[input].Action( );
            } else if ( this->submenus.contains( input ) ) {
                submenus[input].Init( full_path + "/" );
            }
        }
    }

    // Add a submenu
    void Menu::addSubmenu( Menu const &m ) { submenus[m.Name] = m; }

    // Add an action
    void Menu::addItemAction( MenuItem const &m ) {
        actions[m.Name] = m;

        for ( auto const &alias : m.Aliases ) {
            auto aliasAction    = m;
            aliasAction.isAlias = true;

            actions[alias] = aliasAction;
        }
    }

    // Check if the input is a valid command
    bool Menu::isValidCommand( const std::string &input ) {
        bool isBuiltin = std::ranges::find( builtInCommands, input ) != builtInCommands.end( );

        // TODO: Add case-insensitive comparison
        return actions.contains( input ) || submenus.contains( input ) || isBuiltin;
    }
} // namespace ArgoDraft
