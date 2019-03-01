// health_desc.h  健康描述   為了統一 qxd 和 npc 裡的描述……
// naihe 05-9-1 11:35

string get_health_desc( int hp, int hp_max )
{
    if( hp >= hp_max )
        return HIG"看起來健康得很。"NOR;
    if( hp >= (hp_max *9/10) )
        return HIG"似乎受了點兒輕傷，不過毫無影響。"NOR;
    if( hp >= (hp_max *8/10) )
        return HIG"受了點兒輕傷，不過看起來還沒什麼大礙。"NOR;
    if( hp >= (hp_max *6/10) )
        return HIY"氣息開始粗亂，看來似乎受了點兒輕傷。"NOR;
    if( hp >= (hp_max *5/10) )
        return HIY"大口大口地喘著粗氣，看來情形不太妙了。"NOR;
    if( hp >= (hp_max *4/10) )
        return HIR"受傷嚴重，腳步凌亂，眼神散漫，看來需要好好休息一下了。"NOR;
    if( hp >= (hp_max *2/10) )
        return RED"已經受傷過重，一副隨時就要倒下的樣子。"NOR;
    if( hp >= (hp_max *1/10) )
        return RED"已經幾欲倒地，只剩下最後一點氣息在苦苦維系著。"NOR;
    return RED"已經失去了意識，看來是要不行了。"NOR;
}