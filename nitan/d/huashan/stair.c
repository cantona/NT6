//Cracked by Kafei
// xiaolu1.c 華山密室石階
// qfy 10/8/1997

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long",
"石階蜿然向下伸延，盡頭可見扇緊壁著的石門。兩側石壁上掛著點燃\n"
"的火把，把通道照得十分明亮。\n"
);

        set("exits", ([ /* sizeof() == 1 */
                "down" : __DIR__"door",
        ]));


        set("cost", 0);
        setup();
}


