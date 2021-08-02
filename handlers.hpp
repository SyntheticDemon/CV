#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_
#include "data_root.hpp"
#include "server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

class RandomNumberHandler : public RequestHandler
{
public:
  Response *callback(Request *);
};
class RecipeDetailedHandler : public RequestHandler
{
public:
  RecipeDetailedHandler(Menu *menu) { this->menu = menu; }
  Response *callback(Request *);

private:
  Menu *menu;
};
class SignupHandler : public RequestHandler
{
public:
  SignupHandler(Menu *menu) { this->menu = menu; }
  Response *callback(Request *);

private:
  Menu *menu;
};
class RatingHandler : public RequestHandler
{
public:
  RatingHandler(Menu *menu);
  Response *callback(Request *);

private:
  Menu *menu;
};
class LoginHandler : public RequestHandler
{
public:
  LoginHandler(Menu *menu);
  Response *callback(Request *);

private:
  Menu *menu;
};
class AddRecipeShelf : public RequestHandler
{
public:
  AddRecipeShelf(Menu *menu);
  Response *callback(Request *);

private:
  Menu *menu;
};
class DeleteShelfRecipeHandler : public RequestHandler
{
public:
  DeleteShelfRecipeHandler(Menu *menu);
  Response *callback(Request *);

private:
  Menu *menu;
};
class PostRecipeHandler : public RequestHandler
{
public:
  PostRecipeHandler(Menu *menu);
  Response *callback(Request *);

private:
  Menu *menu;
};
class ShelfMenuHandler : public RequestHandler
{
public:
  ShelfMenuHandler(Menu *menu);
  Response *callback(Request *req);

private:
  Menu *menu;
};
class PostShelfHandler : public RequestHandler
{
public:
  PostShelfHandler(Menu *menu);
  Response *callback(Request *req);

private:
  Menu *menu;
};
class ShelfDetailedHandler : public RequestHandler
{
public:
  ShelfDetailedHandler(Menu *menu);
  Response *callback(Request *req);

private:
  Menu *menu;
};
class RecipeDeletionHandler : public RequestHandler
{
public:
  RecipeDeletionHandler(Menu *menu);
  Response *callback(Request *req);

private:
  Menu *menu;
};
class MainMenuHandler : public RequestHandler
{
public:
  MainMenuHandler(Menu *menu);
  Response *callback(Request *req);

private:
  Menu *menu;
};
class UploadHandler : public RequestHandler
{
public:
  Response *callback(Request *);
};
class LogoutHandler : public RequestHandler
{
public:
  LogoutHandler(Menu *menu);
  Response *callback(Request *);

private:
  Menu *menu;
};
#endif
