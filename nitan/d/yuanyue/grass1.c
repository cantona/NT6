// This program is a part of NITAN MudLIB

inherit ROOM; 
void create()
{
        set("short", "芳草坪"); 
        set("long", @LONG
這裏是一塊芳草坪，綠草茵茵，蝴蝶漫舞，花香撲鼻，讓人感到
十分愜意。不禁令人就想一頭躺倒上去，好好的去睡一覺，但這裏偶
爾也會碰到菜花蛇。往西走是片小樹林，北面則是一間卧室。
LONG );
        set("type","grassland");
        set("outdoors", "wansong");
        set("exits",([
                "east":__DIR__"grass2",
                "west":__DIR__"senling1",
                "north":__DIR__"woshi",
                "southeast":__DIR__"shibanlu4",
        ]) );
        
        set("objects",([
                "/clone/beast/caihuashe" : 1,
                __DIR__"obj/greengrass" : 1,
        ]) );
        set("coor/x",-600);
        set("coor/y",240);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
}      
