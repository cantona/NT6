inherit ROOM;

void create()
{
  set("short", "書房");
  set("long", @LONG
這是一間簡陋的書房，中間一張木桌擺着筆墨紙硯，一把小
竹椅放在旁邊，右面放着一個小書架，上面零散的放着幾本書。
LONG
  );
  set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"gd7",
  "enter": __DIR__"xiaoting",
]));
        set("objects", ([
        CLASS_D("yaowang") + "/wuchen" : 1,
]));
  setup();
  replace_program(ROOM);
}

