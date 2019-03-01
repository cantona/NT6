inherit ROOM;
void create()
{
        set("short", "金冠巨蟒洞"); 
        set("long", @LONG
爬了許久，洞道漸寬，到了此處，便豁然開朗，已可站直身軀。
你定睛一瞧，不禁大驚失色，洞中霍然有條長達數丈，粗若水桶的金
冠巨蟒盤旋其中，一對碧眼如炬，爍然放光。洞中骸骨遍地，腥臭異
常，積滿穢物。
LONG );
        set("indoors", "wansong");
        set("type","mountain");
        set("exits",([
                "south":__DIR__"shandong",
        ]) );
        set("objects", ([
                "/clone/beast/xuanmang" : 1,
                __DIR__"obj/skeleton" : 2,
        ]) ); 
        set("coor/x",-610);
        set("coor/y",300);
        set("coor/z",80);
        set("refresh_all_items", 1);
        setup();
} 
