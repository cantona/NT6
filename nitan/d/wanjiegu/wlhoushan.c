// Room: /d/wanjiegu/wlhoushan.c

inherit ROOM;

void create()
{
        set("short", "後山");
        set("long", @LONG
這裏是無量山的後山，你四處看了看，還是無法找到上山的路徑。
眼前有一片湖泊，看上去幽靜安然。遠遠的看過去，對面山壁十分光
滑，宛若一面鏡子。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([ /* sizeof() == 2 */
                "northeast" : __DIR__"wlroad2",
        ]));

        setup();
}