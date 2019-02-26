// Room: /d/mobei/maowu.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "小茅屋");
        set("long", @LONG
幾根粗糙的木頭搭起一個架子，上面的樹皮都還沒剝落。塞北草原
長長的茅草覆蓋在木頭上，組成這個小茅屋。裏面的一切都是江南模式，
用木頭草草搭起的牀，一邊是個泥土灶，一邊的牆上還開了個小窗。
LONG
        );
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/liping" : 1,
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "out" : __DIR__"caodui",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -190);
        set("coor/y", 5160);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}