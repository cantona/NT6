// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "圓月山莊大門");
        set("long", @LONG
路到盡頭，便是聞名天下的『圓月山莊』的大門。乍一望去，大
門樑上雕龍刻鳳，美奐美侖，不知凝聚著多少能工巧匠的心血。不禁
讓人以為莊主定是富有顯貴之人。門前左右各蹲著一只威武莊嚴的石
獅子。但定睛細瞧，則讓人喟嘆不己，原來門上鏽跡斑斑，滿是灰塵，
紅漆也已剝落大半，莫名之中讓人產生一種凄涼的感覺。
LONG );
        set("outdoors", "yuanyue");
        set("type", "street");
        set("exits",([
                "south":__DIR__"shandao2",
                "enter":__DIR__"suishilu1",
        ]) );

        set("coor/x",-590);
        set("coor/y",200);
        set("coor/z",80);
        
        setup();
        
        replace_program(ROOM);
} 
