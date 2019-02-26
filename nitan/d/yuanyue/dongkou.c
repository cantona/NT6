inherit ROOM;
void create()
{
        set("short", "洞口"); 
        set("long", @LONG
路至盡頭，便是神祕山洞的洞口，刺鼻的腥氣愈發令人窒息，洞
口旁一塊木牌歪倒在地，你湊上去擦去木牌上的泥垢，只見上面模模
糊糊刻着『洞中惡蟒襲人，勿入！切切』云云。
LONG );
        set("outdoors", "fugui");
        set("type","mountain");
        set("exits",([
                "enter":__DIR__"shandong",
                "southwest":__DIR__"senling4",
        ]) ); 
        set("coor/x",-610);
        set("coor/y",280);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
}     
