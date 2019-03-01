inherit ROOM;

void create()
{
        set("short", "冰道");
        set("long", @LONG
這條冰道的兩邊都很安靜。西邊是冰車，東邊是凌霄城的監
獄。北邊過去，就是凌霄城的根本之地----雪山派的總堂凌霄殿
了，這裡防守緊密，四處都是凌霄弟子。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "south" : __DIR__"iceroad2",
                    "north" : __DIR__"meiroad1",
                    "west"  : __DIR__"car",
                    "east"  : __DIR__"jianyuting",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 2,
        ]));
        setup();
        replace_program(ROOM);
}
