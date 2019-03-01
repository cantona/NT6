inherit ROOM;
void create()
{
        set("short", "鬆林"); 
        set("long", @LONG
這裡是圓月山莊後園一片密密的鬆木林，四周一片寂靜。鬆針落
的遍地都是，幾乎把整個小路舖成了條軟軟的鬆毯，不知名的野兔偷
偷逃過，小路旁就是條靜靜流淌的小溪，溪水上漂浮著鬆針黃葉，盪
開枝葉，依稀可看到溪水碧綠如鏡，清澈見底。
LONG );
        set("outdoors", "wansong");
        set("type","forest");
        set("exits",([
                "east":__DIR__"grass1",
                "northwest":__DIR__"senling2",
        ]) );
        
        set("objects", ([
                CLASS_D("mojiao/fuhongxue") : 1,
        ]));
        set("coor/x",-610);
        set("coor/y",240);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
}   
