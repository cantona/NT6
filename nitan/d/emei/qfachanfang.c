inherit ROOM;

void create()
{
      set("short", "禪房");
        set("long", @LONG
這裡是一間安靜寬敞的禪房，乃是千佛庵中弟子打坐修行之所。
地下整整齊齊放著許多蒲團。幾位年輕師太和俗家女弟子正肅容入定。
LONG );
      set("exits", ([
          "west" : __DIR__"qfadadian",
      ]));
      set("sleep_room", 1);
      set("no_clean_up", 0);
      set("no_fight", 1);
      set("coor/x", -460);
        set("coor/y", -240);
        set("coor/z", 100);
        set("coor/x", -460);
        set("coor/y", -240);
        set("coor/z", 100);
        setup();
      replace_program(ROOM);
}