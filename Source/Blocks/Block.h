class Block
{
 protected:
  //Position of the block
  int abs, ord;
  //Player
  Player* player;
  //File where the block's texture can be found
  string texture;
 public:
  block(int x, int y, Player* player, string text);
  int get_abs();
  int get_ord();
  int get_player_abs();
  int get_player_ord();
  string get_texture();
}
