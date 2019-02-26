inherit ROOM;

void create()
{
      set("short", "禪房");
        set("long", @LONG
這裏便是峨嵋華藏庵的禪房。地下散亂地放着許多蒲團木魚等，
此處正是本派弟子打坐修行之所。幾位年輕師太和俗家女弟子正肅容
入定。禪房後面有一道門通往華藏庵休息室，北邊的走廊通向廣場。
LONG );
      set("exits", ([
          "north" : __DIR__"hcawest2", 
          "south" : __DIR__"hcaxiuxishi", 
      ]));
      set("sleep_room", 1);
      set("no_fight", 1);
      set("no_clean_up", 0);
      setup();
      replace_program(ROOM);
}