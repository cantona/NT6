inherit ROOM;

void create()
{
        set("short", "荊棘叢");
        set("long", @LONG
這裏是一片茂密的荊棘叢，中間隱隱約約有一條小道，叢中
開着一些不知名的小花，空氣中瀰漫着一種刺鼻的味道。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"jingji2",
  "south" : __DIR__"xiaolu1",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
