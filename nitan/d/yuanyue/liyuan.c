// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "梨園"); 
        set("long", @LONG
這裏便是圓月山莊的『聖地』梨園，之所以這樣説，因為對柳若
鬆他來説，這兒不僅意味着餓了可以拿幾隻梨子充飢，更加重要的是，
酒蟲上來了，也能摘幾筐梨拿去換酒喝，時已深秋，梨樹上原本還有
滿樹又甜又大的梨子，但現在卻已經被摘得幾乎所剩無幾了。
LONG );
        set("type","forest");
        set("outdoors", "wansong");
        set("exits",([
                "west":__DIR__"shibanlu2",
        ]) );

        set("objects",([
                CLASS_D("mojiao/yinlong") : 1,
        ]) );
        
        set("coor/x",-570);
        set("coor/y",220);
        set("coor/z",80);
        setup(); 
} 
