// Room: /d/wuyi/yuchayuan.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "御茶園");
        set("long", @LONG
御茶園位于四曲南邊的一塊平地上。元初，一個叫高興的官吏為了
媚上，向皇帝獻了幾斤武夷“石乳”。從此，年年二十斤的“石乳”就
成了歷任崇安縣令的政績。為防以次充好，高興最後還是上奏皇帝，在
此建起了盛極一時的御茶園。每年“驚蟄”那一天，喊山台上陣陣“茶
發芽了，茶發芽了！”的呼叫聲，時時扣擊著歲月的期盼。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"tongxianjing",
                "north" : __DIR__"5qu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1380);
        set("coor/y", -5020);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
