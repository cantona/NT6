inherit ROOM;

void create()
{
        set("short", "小院");
        set("long", @LONG
這裡是一處寂靜的小院落，周圍是用青竹紮就的籬笆，地上
長著嫩綠的小草，院子中央擺著一長園石桌，桌子邊上有幾個石
礅，石桌和石礅表面都非常光滑，好像經常有人坐在這裡。
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
