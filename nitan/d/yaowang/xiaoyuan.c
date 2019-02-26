inherit ROOM;

void create()
{
        set("short", "小院");
        set("long", @LONG
這裏是一處寂靜的小院落，周圍是用青竹扎就的籬笆，地上
長着嫩綠的小草，院子中央擺着一長園石桌，桌子邊上有幾個石
礅，石桌和石礅表面都非常光滑，好像經常有人坐在這裏。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"gd1",
  "south" : __DIR__"bridge1",
  "east" : __DIR__"lawn",
  "west" : __DIR__"well",
]));

        set("outdoors", "yaowang");

        setup();
        replace_program(ROOM);
}
