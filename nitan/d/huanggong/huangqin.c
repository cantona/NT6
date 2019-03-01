// Room: /d/huanggong/huangqin.c

inherit ROOM;

void create()
{
        set("short", "懋勤殿");
        set("long", @LONG
這是皇上放置圖書翰墨以及內廷儒臣值班的懋勤殿。乾隆帝少年時
曾在此讀書。此處藏書甚多，多為內府編刊的各類新書。天下刑法人命
關天。每年秋後，在此審斷一次，故稱“秋審”。後世“秋後算賬”也
是源于此。被朱筆劃勾者，斷無生理，稱“勾到”或“勾決”。因在懋
勤殿勾決，故又稱“懋勤殿勾到”。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "east" : __DIR__"qianqinggong",
        ]));
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/wenyoufang" : 1,
        ]));

	set("coor/x", -2820);
	set("coor/y", 7751);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}