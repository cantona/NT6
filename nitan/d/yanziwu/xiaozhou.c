// Room: /d/yanziwu/xiaozhou.c
// Date: Feb.14.1998 by Java

inherit ROOM;
void create()
{
        set("short", "小舟");
        set("long", @LONG
碧綠湖面飄盪的一葉小舟，一個綠衫少女手執雙槳，緩緩劃水，
口中唱著吳儂小曲。歌聲嬌柔無那，歡悅動心。一雙纖手皓膚如玉，
映著綠波，便如透明一般。
LONG );
        set("outdoors", "yanziwu");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
