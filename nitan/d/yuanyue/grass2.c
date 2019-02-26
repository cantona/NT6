// This program is a part of NITAN MudLIB

inherit ROOM; 
void create()
{
        set("short", "芳草坪"); 
        set("long", @LONG
這裏是一塊芳草坪，綠草茵茵，蝴蝶漫舞，花香撲鼻，讓人感到
十分愜意。不禁令人就想一頭躺倒上去，好好的去睡一覺，但這裏偶
爾也會碰到菜花蛇。
LONG );
        set("type","grassland");
        set("outdoors", "fugui");
        set("exits",([
                "east":__DIR__"grass3",
                "west":__DIR__"grass1",
        ]) );
        set("objects",([
               "/clone/beast/caihuashe" : 1,
                __DIR__"obj/greengrass" : 1,
        ]) );
        set("coor/x",-590);
        set("coor/y",240);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
}
