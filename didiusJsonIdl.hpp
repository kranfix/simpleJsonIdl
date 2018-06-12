/* Created by Frank Moreno (Kranfix) on June 12th, 2018 */
class DataFrame {
  int off; // offset

  char * buf; // Buffer
  int n;

public:
  DataFrame(char * buf, char * type, char * id);

  void reset();
  void addInt(char * key, int val);
  void addFloat(char * key, float val);
  void Dht(float t, float h);
  void Acc(float x, float y, float z);

  void close();
  int len();
};