#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include "raw_logic/UserModel.hpp"
#include "data_root.hpp"
using namespace std;

int main(int argc, char **argv)
{
    srand(time(NULL)); // for rand
    Menu *new_menu = new Menu();
    try
    {
        MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
        server.setNotFoundErrPage("static/404.html");
        server.get("/signup", new ShowPage("static/signup.html"));
        server.post("/signup", new SignupHandler(new_menu));
        server.get("/home", new ShowPage("static/home.html"));
        server.get("/bad_request", new ShowPage("static/bad_request.html"));
        server.get("/permission_denied", new ShowPage("static/permission_denied.html"));
        server.get("/not_found", new ShowPage("static/not_found.html"));
        server.get("/", new ShowPage("static/home.html"));
        server.get("/login", new ShowPage("static/login.html"));
        server.post("/login", new LoginHandler(new_menu));
        server.get("/menu", new MainMenuHandler(new_menu));
        server.get("/logout", new LogoutHandler(new_menu));
        server.get("/recipes_detailed", new RecipeDetailedHandler(new_menu));
        server.post("/post_recipe", new PostRecipeHandler(new_menu));
        server.post("/rate", new RatingHandler(new_menu));
        server.get("/delete_recipes", new RecipeDeletionHandler(new_menu));
        server.get("/shelves", new ShelfMenuHandler(new_menu));
        server.post("/post_shelf", new PostShelfHandler(new_menu));
        server.get("/shelf_detail", new ShelfDetailedHandler(new_menu));
        server.post("/add_shelf_recipe", new AddRecipeShelf(new_menu));
        server.post("/delete_shelf_recipe", new DeleteShelfRecipeHandler(new_menu));
        server.run();
    }
    catch (Server::Exception e)
    {
        cerr << e.getMessage() << endl;
    }
}