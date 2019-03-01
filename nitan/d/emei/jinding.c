inherit ROOM;

void create()
{
              set("short", "金頂");
        set("long", @LONG
這就是峨嵋山的主峰金頂。此峰聳立大地，高入雲表，秀麗而又
壯美，李白讚頌它：『青冥倚天開，彩錯疑畫出』登上金頂，視野豁
然開朗，鳥看腳下，但見群峰湧綠疊翠，三江如絲如帶；回首遠眺，
則見大雪山橫亙天際，貢嘎山直插蒼穹。
LONG );
        set("no_sleep_room",1);
              set("outdoors", "emei");

              set("objects", ([
                   CLASS_D("emei") + "/fengling" : 1,
              ]));
              set("exits",([
                  "northdown" : __DIR__"wanxingan",
                  "southwest" : __DIR__"woyunan", 
                  "southeast" : __DIR__"huacangan",
              ]));

              set("no_clean_up", 0);
              set("coor/x", -570);
        set("coor/y", -310);
        set("coor/z", 220);
        setup();
}