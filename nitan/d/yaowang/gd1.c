inherit ROOM;
/*
string go_enter(object me)
{
        if( me && (query("family/family_name", me) == "藥王谷") )
                return __DIR__"dmq";

        else
                return __DIR__"shulin/entry";
}
*/
void create()
{
        set("short", "石子小路");
        set("long", @LONG
這是一條石子小路蜿蜒在青青的綠草地中，可能是經常有人
走動，路上的石子被磨得非常光亮，仔細看上面還有用彩色的石
子拼出的一個“藥”字。路邊豎著一塊小石碑(bei)。
LONG
        );

        set("exits", ([
  "north" : __DIR__"dmq",
  "south" : __DIR__"xiaoyuan",
]));

        set("outdoors", "yaowang");
        setup();
}
