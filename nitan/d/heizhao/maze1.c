// Code of ShenZhou
// maze1.c

inherit ROOM;

int do_find(string);

void create()
{
        set("short", "密林矮樹");
        set("long", @LONG
你來到了一片黑森森的樹林面前，放眼望去，密密麻麻的都是樹
木，而且荊棘叢生，隱約可見有些小路東盤西曲。你仔細觀察，發現
這顯然是個人造的迷宮。其中暗合五行八卦，奇門遁甲，端的非同小
可，千萬不要冒然進去。
LONG );
        set("exits", ([
                "west" : __DIR__"maze2",
                "east" : __DIR__"shanlu1",
                ]));

        set("cost", 2);
        set("outdoors", "heizhao");
        set("coor/x", -38000);
        set("coor/y", -71010);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir=="west") {
                if (! userp(me)) return 0;
                set_temp("mark/maze金", 1, me);
                set_temp("mark/maze木", 1, me);
                set_temp("mark/maze水", 1, me);
                set_temp("mark/maze火", 1, me);
                set_temp("mark/maze土", 1, me);
                set_temp("mazepath", 11111+random(88889), me);
        }

        return ::valid_leave(me, dir);
}