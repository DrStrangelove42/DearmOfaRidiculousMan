class block
{
 protected:
  //Position of the block
  int abs, ord;
  //Player's position
  int *player_abs, *player_ord;
  //File where the block's texture can be found
  string texture;
 public:
  block(int x, int y, int* player_x, int* player_y, string text);
  int get_abs();
  int get_ord();
  int get_player_abs();
  int get_player_ord();
  string get_texture();
}
