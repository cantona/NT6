inherit ROOM;

void create()
{
       set("short","芙蓉洞外");
        set("long", @LONG
只見此處有一個小洞，洞口狹小，只能容一人通過。洞中卻射出
一縷陽光。
LONG );
       set("exits",([
              "enter":__DIR__"furong1",
       ]));
        
       setup();
       replace_program(ROOM);
}