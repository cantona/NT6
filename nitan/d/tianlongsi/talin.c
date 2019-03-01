inherit ROOM;

void create()
{
        set("short", "塔林");
        set("long", @LONG
這是一片塔林。放眼望去，林林總總有不下百座高矮不一的石塔，
這些都是達官顯貴們捐資修築的，或是為了祈求菩薩保佑，或是為了
還願平心。東西北三面各有一座高塔。
LONG );
        set("outdoors", "tianlongsi");
        set("exits", ([
                "south" : __DIR__"ta1",
                "west" : __DIR__"ta3",
                "east" : __DIR__"ta2",
                "north" : __DIR__"damen",
        ]));
        set("objects",([
                __DIR__"npc/saodiseng" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}