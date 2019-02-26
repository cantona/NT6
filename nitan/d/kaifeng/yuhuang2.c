inherit ROOM;

void create()
{
        set("short", "玉皇閣二層");
        set("long", @LONG
閣樓中打掃得還算乾淨，看來道士們對於三清雖然不大在意，對
玉皇還是挺尊重的。此地供奉的是尊漢白玉雕玉皇大帝像，紋理細膩，
推開窗欄，還能看到繁華的開封街景。
LONG );
        set("objects", ([
                  __DIR__"npc/obj/yudixiang" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "down" : __DIR__"yuhuang",
        ]));

	set("coor/x", -5100);
	set("coor/y", 2240);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}