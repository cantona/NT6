int main(object me,string arg)
{
        //Look  score  hp  search  say   chat  chann  I   fee  who  map  help  alias  icon  
        string *cmdbar;
        string *tmp = ({
                "觀察=look","物品=i","評價ＳＣ=score","狀態ＨＰ=hp",
                "功夫ＳＫ=cha","設置頭像=face ...","查詢費用=fee",
                "設置頻道=chann","搜索=search","在線=who",
                "幫助=help ...","説話=say ...","閒聊=chat ...",});

        
        cmdbar=query("cmdbar", me);
        if(!arrayp ( cmdbar ) || sizeof(cmdbar)!=13)
                cmdbar = tmp;
        //me->set("cmdbar",cmdbar);//以後如果受玩家歡迎的話可以允許他們自己定義命令（關閉重新運行後生效）
        write(TMI("cmdbar "+implode(cmdbar,";")+";"));
        return 1;
}