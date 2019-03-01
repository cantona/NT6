// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "臥室"); 
        set("long", @LONG
這裡是圓月山莊的臥室。屋子不大，也沒什麼擺設，亂七八糟扔
著些破破爛爛的舊衣物，牆角布滿了蜘蛛網，滿屋子都是灰塵，嗆的
你不住咳嗽。
LONG );
        set("type","indoors");
        set("sleep_room", 1);
        set("no_fight", 1); 
        set("exits",([
                "east":__DIR__"grass4",
                "south":__DIR__"grass1",
        ]) ); 

        set("coor/x",-600);
        set("coor/y",250);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
}      
