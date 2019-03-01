inherit ROOM;

void create()
{
        set("short", "荊棘叢");
        set("long", @LONG
這裡是一片茂密的荊棘叢，中間隱隱約約有一條小道，叢中
開著一些不知名的小花，空氣中彌漫著一種刺鼻的味道。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"shangpo1",
  "south" : __DIR__"jingji1",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}