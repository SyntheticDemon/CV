#include "handlers.hpp"
#include "raw_logic/main_header.hpp"
using namespace std;
#include <string>
class Recipe;
ShelfDetailedHandler::ShelfDetailedHandler(Menu *menu)
{
  this->menu = menu;
}
Response *ShelfDetailedHandler::callback(Request *req)
{
  string body;
  Response *res = new Response();
  vector<string> command = {NODIF, NODIF, NODIF, NODIF, req->getQueryParam("shelf_id")};
  string sid = req->getQueryParam("sid");
  UserModel *current_user = this->menu->user_search(sid, command);
  int shelf_id = menu->shelf_search(command, false, current_user) - 1;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body>";
  body += "<div style='text-align: center ;float: left; border-radius: 2px; border-color: black; border-style: double;'>";
  body += "<form method ='post' action='/add_shelf_recipe?sid=" + sid + "&shelf_id=" + to_string(shelf_id + 1) + "'>";
  body += "Add recipe to shelf";
  body += "<br>";
  body += "<br>";
  body += "<br>";
  body += "Recipe ID<br>";
  body += "<input type = 'number' name = 'recipe_id' style = 'border-radius:10px;margin-left: 40 px;'>";
  body += "<br>";
  body += "<button type = 'submit'> Add recipe to shelf</button>";
  body += " </form>";
  body += "</div>";
  for (int i = 0; i < menu->shelves[shelf_id]->get_recipes().size(); i++)
  {
    body += "<div style='text-align: center; width:400px;; border-radius: 10px;background-color:silver; border-color: gray; border-style: double;'>";
    body += "<a href='/recipes_detailed";
    body += "?id=";
    body += to_string(menu->shelves[shelf_id]->get_recipes()[i]->get_id());
    body += "&sid=";
    body += sid;
    body += "'>";
    body += menu->shelves[shelf_id]->get_recipes()[i]->get_recipe_name();
    body += "<br>";
    body += menu->shelves[shelf_id]->get_recipes()[i]->get_id();
    body += "<br>";
    body += "Vegetarian :";
    body += menu->shelves[shelf_id]->get_recipes()[i]->get_vegetarian();
    body += "<br>";
    body += "Preperation Time :";
    body += menu->shelves[shelf_id]->get_recipes()[i]->get_time();
    body += "</a>";
    body += "<form method ='post' action='/delete_shelf_recipe?shelf_id=" + to_string(shelf_id + 1) + "&sid=" + sid + "&recipe_id=" + to_string(menu->shelves[shelf_id]->get_recipes()[i]->get_id());
    body += "'>";
    body += "<button type='submit'>Delete this recipe from the shelf</button>";
    body += "</div>";
    body += "<br>";
  }
  body += "<div style='text-align: left;'>";
  body += "<div style='float:right;'>";
  body += "<a style='margin-left: 15px;' href='/logout?sid=" + sid;
  body += "'>logout</a>";
  body += "<a style='margin-left: 15px;' href='/recipes'>recipes</a>";
  body += "</div>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res->setHeader("Content-Type", "text/html");
  res->setBody(body);
  return res;
}
AddRecipeShelf::AddRecipeShelf(Menu *menu)
{
  this->menu = menu;
}
Response *AddRecipeShelf::callback(Request *req)
{
  string body;
  Response *res = new Response();
  string sid = req->getQueryParam("sid");
  vector<string> command = {PUT, SHELVES_RECIPES, ARG_FOLLOWS, SHELF_ID, req->getQueryParam("shelf_id"), RECIPE_ID, req->getBodyParam("recipe_id")};
  UserModel *current_user = this->menu->user_search(sid, command);
  try
  {
    menu->shelf_recipe_commands(command, current_user);
  }
  catch (Exception exception)
  {
    res = res->redirect(exception.get_err());
    return res;
  }
  string redirection = "/shelves?sid=" + sid;
  res = res->redirect(redirection);
  return res;
}
DeleteShelfRecipeHandler::DeleteShelfRecipeHandler(Menu *menu)
{
  this->menu = menu;
}
Response *DeleteShelfRecipeHandler::callback(Request *req)
{
  string body;
  Response *res = new Response();
  string sid = req->getQueryParam("sid");
  vector<string> command = {DELETE, SHELVES_RECIPES, ARG_FOLLOWS, SHELF_ID, req->getQueryParam("shelf_id"), RECIPE_ID, req->getQueryParam("recipe_id")};
  UserModel *current_user = this->menu->user_search(sid, command);
  try
  {
    menu->shelf_recipe_commands(command, current_user);
  }
  catch (Exception exception)
  {
    res = res->redirect(exception.get_err());
    return res;
  }
  string redirection = "/shelves?sid=" + sid;
  res = res->redirect(redirection);
  return res;
}
PostShelfHandler::PostShelfHandler(Menu *menu)
{
  this->menu = menu;
}
Response *PostShelfHandler::callback(Request *req)
{
  string body;
  Response *res = new Response();
  string sid = req->getQueryParam("sid");
  vector<string> command = {POSTT, SHELVES, ARG_FOLLOWS, NAME, req->getBodyParam("title")};
  UserModel *current_user = this->menu->user_search(sid, command);
  try
  {
    menu->handle_shelves(command, current_user);
  }
  catch (Exception exception)
  {
    res = res->redirect(exception.get_err());
    return res;
  }
  string redirection = "/shelves?sid=" + sid;
  res = res->redirect(redirection);
  return res;
}
ShelfMenuHandler::ShelfMenuHandler(Menu *menu)
{
  this->menu = menu;
}
Response *ShelfMenuHandler::callback(Request *req)
{
  string body;
  Response *res = new Response();
  string sid = req->getQueryParam("sid");
  vector<string> command;
  UserModel *current_user = menu->user_search(sid, command);
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body>";
  body += "<div style='text-align: center ;float: left; border-radius: 2px; border-color: black; border-style: double;'>";
  body += "<form method ='post' action='/post_shelf?sid=" + sid + "'>";
  body += "Post a shelf<br>";
  body += "<br>";
  body += "<br>";
  body += "Shelf Name<br>";
  body += "<input type = 'text' name = 'title' style = 'border-radius:10px;margin-left: 40 px;'>";
  body += "<br>";
  body += "<br>";
  body += "<button type = 'submit'> add shelf</button>";
  body += " </form>";
  body += "</div>";
  body += "<div style='text-align: left;'>";
  body += "<div style='float:right;'>";
  body += "<a style='margin-left: 15px;' href='/logout?sid=" + sid;
  body += "'>logout</a>";
  body += "<a style='margin-left: 15px;' href='/recipes'>recipes</a>";
  body += "</div>";
  body += "</div>";
  body += "<div style='text-align: center;margin-left:500px;'>";
  body += "<h4>Shelves </h4>";
  for (int i = 0; i < menu->shelves.size(); i++)
  {
    body += "<div style='text-align: center; width:400px;; border-radius: 10px;background-color:silver; border-color: gray; border-style: double;'>";
    if (menu->shelves[i]->owner->get_username() == sid)
    {
      body += "<a href='/shelf_detail?shelf_id=" + to_string(menu->shelves[i]->get_id()) + "&sid=" + sid + "'>";
      body += menu->shelves[i]->get_shelf_name();
      body += "</a>";
    }
    body += "</div>";
    body += "<br>";
  }
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res->setHeader("Content-Type", "text/html");
  res->setBody(body);
  return res;
}
Response *SignupHandler ::callback(Request *req)
{
  Response *res = new Response();
  res->setHeader("Content-Type", "text/html");
  string body;
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string type = req->getBodyParam("type");
  vector<string> command = {"POST", SIGNUP, ARG_FOLLOWS, USERNAME, username, PASSWORD, password, TYPE, type};
  try
  {
    menu->signup(command);
  }
  catch (Exception exception)
  {
    res = res->redirect(exception.get_err());
    return res;
  }
  res = res->redirect("/login");
  return res;
}
LoginHandler::LoginHandler(Menu *menu)
{
  this->menu = menu;
}
Response *RecipeDeletionHandler::callback(Request *req)
{
  string username = req->getQueryParam("sid");
  string body;
  Response *res = new Response();
  Recipe *current;
  vector<string> command;
  UserModel *current_user;
  try
  {
    vector<string> command = {DELETE, RECIPES, ARG_FOLLOWS, req->getQueryParam("id")};
    current_user = menu->user_search(username, command);
    current_user->delete_recipes(command, menu->recipe_search(stoi(req->getQueryParam("id"))), menu->recipes);
  }
  catch (Exception e)
  {
    res = res->redirect(e.get_err());
    return res;
  }
  string redirection = "/menu?sid=" + username;
  res = res->redirect(redirection);
  return res;
}
RecipeDeletionHandler::RecipeDeletionHandler(Menu *menu)
{
  this->menu = menu;
}
Response *LoginHandler::callback(Request *req)
{
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  Response *res = new Response();
  vector<string> command = {"POST", LOGIN, ARG_FOLLOWS, USERNAME, username, PASSWORD, password};
  try
  {
    UserModel *CurrentUser = menu->user_search(username, command);
    if (CurrentUser->get_logged_in() == true)
    {
      throw(Exception(PERMISSION_DENIED));
    }
    else
    {
      menu->login(command, CurrentUser);
    }
  }
  catch (Exception exception)
  {
    res = res->redirect(exception.get_err());
    return res;
  }
  string redirection = "/menu?sid=" + username;
  res = res->redirect(redirection);
  return res;
}
MainMenuHandler::MainMenuHandler(Menu *main_menu)
{
  this->menu = main_menu;
}
PostRecipeHandler::PostRecipeHandler(Menu *menu)
{
  this->menu = menu;
}
Response *PostRecipeHandler::callback(Request *req)
{
  string username = req->getQueryParam("sid");
  Response *res = new Response();
  vector<string> command;
  try
  {
    command = {POSTT, RECIPES, ARG_FOLLOWS, RECIPE_TITLE,
               req->getBodyParam("title"), INGREDIENTS, req->getBodyParam("ingredients"),
               VEGETARIAN, req->getBodyParam("Vegeterian"), "time_to_ready", req->getBodyParam("preperation_time"), TAGS, req->getBodyParam("tags"),
               "image_adress", NODIF};
    menu->general_recipe(command, menu->user_search(username, command));
  }
  catch (Exception e)
  {
    res = res->redirect(e.get_err());
    return res;
  }
  string redirection = "/menu?sid=" + username;
  res = res->redirect(redirection);
  return res;
}
LogoutHandler::LogoutHandler(Menu *menu)
{
  this->menu = menu;
}
Response *LogoutHandler::callback(Request *req)
{
  Response *res = new Response();
  vector<string> command;
  try
  {
    menu->logout(menu->user_search(req->getQueryParam("sid"), command));
    res = res->redirect("/home");
    return res;
  }
  catch (Exception exception)
  {
    res = res->redirect(exception.get_err());
    return res;
  }
}
RatingHandler::RatingHandler(Menu *menu)
{
  this->menu = menu;
}
Response *RatingHandler::callback(Request *req)
{
  string body;
  string username = req->getQueryParam("sid");
  Response *res = new Response();
  Recipe *current;
  vector<string> command;
  UserModel *current_user;
  try
  {
    command = {POSTT, RATES, ARG_FOLLOWS, RECIPE_ID, req->getQueryParam("id"), SCORE, req->getBodyParam("score")};
    UserModel *current_user = menu->user_search(username, command);
    current = menu->recipes[menu->recipe_search(stoi(req->getQueryParam("id")))];
    current_user->rate(current, stoi(req->getBodyParam("score")), command);
  }
  catch (Exception e)
  {
    res = res->redirect(e.get_err());
    return res;
  }
  string redirection = "/menu?sid=" + username;
  res = res->redirect(redirection);
  return res;
}
Response *RecipeDetailedHandler::callback(Request *req)
{
  string body;
  Response *res = new Response();
  string username = req->getQueryParam("sid");
  Recipe *current;
  vector<string> command;
  UserModel *current_user;
  try
  {
    current_user = menu->user_search(username, command);
    current = menu->recipes[menu->recipe_search(stoi(req->getQueryParam("id")))];
  }
  catch (Exception e)
  {
    res = res->redirect(e.get_err());
    return res;
  }
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body>";
  body += "<div style='float:right;'>";
  body += "<a style='margin-left: 15px;' href='/shelves";
  body += "?sid=" + username + "'>";
  body += "shelves</a>";
  body += "<a style='margin-left: 15px;' href='/logout?sid=" + username;
  body += "'>logout</a>";
  body += "<a style='margin-left: 15px;' href='/recipes'>recipes</a></div>";
  body += "<div style='text-align: center; width:800px;; border-radius: 10px;background-color:silver; border-color: gray; border-style: double;'>";
  body += "<h4>Recipe Name </h4>";
  body += current->get_recipe_name();
  body += "<h4>Recipe ID </h4>";
  body += to_string(current->get_id());
  body += "<h4>Recipe Rating </h4>";
  body += to_string(current->get_rating());
  body += "<h4>Vegetarian </h4>";
  body += current->get_vegetarian();
  body += "<h4>Tags </h4>";
  for (auto i : current->get_tags())
  {
    body += " " + i;
  }
  body += "<h4>Ingredients </h4>";
  for (auto i : current->get_ingredients())
  {
    body += " " + i;
  }
  body += "<h4>Ingredients </h4>";
  body += "<form action='/rate?";
  body += "id=";
  body += to_string(current->get_id());
  body += "&sid=";
  body += username;
  body += "'";
  body += "method='post'>";
  body += "<span>";
  body += "<input type='radio' name='score' value='1'> 1";
  body += "<br>";
  body += "<input type='radio' name='score' value='2'> 2";
  body += "<br>";
  body += "<input type='radio' name='score' value='3'> 3";
  body += "<br>";
  body += "<input type='radio' name='score' value='4'> 4";
  body += "<br>";
  body += "<input type='radio' name='score' value='5'> 5";
  body += "</span>";
  body += "<br>";
  body += "<br>";
  body += "<button style = 'height: 50px; width:100px;' type = 'submit'> Rate";
  body += "</ button>";
  body += " </ form>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res->setHeader("Content-Type", "text/html");
  res->setBody(body);
  return res;
}
Response *MainMenuHandler::callback(Request *req)
{
  string body;

  Response *res = new Response();
  UserModel *current;
  vector<string> command;
  try
  {
    current = menu->user_search(req->getQueryParam("sid"), command);
  }
  catch (Exception e)
  {
    res = res->redirect(e.get_err());
    return res;
  }
  res = current->give_menu_response(req, menu);
  return res;
}
/*map<string, string> ColorHandler::handle(Request *req)
{
  map<string, string> context;
  string newName = "I am " + req->getQueryParam("name");
  context["name"] = newName;
  context["color"] = req->getQueryParam("color");
  return context;
}
*/