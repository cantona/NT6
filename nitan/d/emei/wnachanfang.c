inherit ROOM;

void create()
{
      set("short", "禪房");
        set("long", @LONG
這裡是一間安靜寬敞的禪房，乃是庵中弟子打坐修行之所。地下
整整齊齊地放著許多蒲團。幾位年輕師太和俗家女弟子正肅容入定。
LONG );
      set("exits", ([
          "west" : __DIR__"wnadian",
      ]));
      set("sleep_room", 1);
      set("no_clean_up", 0);
      set("no_fight", 1);
        set("coor/x", -460);
        set("coor/y", -220);
        set("coor/z", 90);
        setup();
      replace_program(ROOM);
}