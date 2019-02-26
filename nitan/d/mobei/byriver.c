// Room: /d/mobei/byriver.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "水塘邊");
        set("long", @LONG
草原上的一個小水塘，邊上是幾棵半枯萎的老樹。塘邊的青草半拖
了到水中，塘水有些渾濁。塘的北邊是個畜欄，東面是個乾草堆，旁邊
的一間小茅屋雖然簡陋，依然能看出江南的風格。
LONG
        );
        set("outdoors", "mobei");
        set("exits", ([ /* sizeof() == 3 */
                "southwest" : __DIR__"river",
                "northeast" : __DIR__"chulan",
                "east" : __DIR__"caodui",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -200);
        set("coor/y", 5160);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}