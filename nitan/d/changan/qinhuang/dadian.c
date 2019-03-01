// This is a room made by wsl.
inherit ROOM;
void create()
{
    set("short", "大殿");
        set("long", @LONG
這一大片空間的高度並不是很高，可是在上面，星月夜空，由無
數小的油燈作為照明之用，看起來，真像是在曠野之中看夜空。而地
面上，有一道相當寬闊的河流，河水潺潺流過，但是在流的卻是----
『水銀』。
LONG );
    set("exits", ([
        "north" :__DIR__"dadian2",
]));
    setup();
    replace_program(ROOM);
}
