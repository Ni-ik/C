# Программа расчёта оптимального коэффициента загрузки электрической сети


- Полезный отпуск электроэнергии
W=S_"НОМ" ⋅cos⁡( ϕ)⋅T_"НАИБ" 
- Суммарные потери ЭЭ холостого хода
ΔW=ΔW_"ХХ" +ΔW_"НАГР" 
- Потери ЭЭ холостого хода
ΔW_"ХХ" =ΔP_"ХХ" ⋅T
- Нагрузочные потери ЭЭ
ΔW_"НАГР" =ΔW_"НЛ" +ΔW_"НТ" 
- Нагрузочные потери ЭЭ в линиях
ΔW_"НЛ" =ΔP_"НЛ" ⋅τ
- Нагрузочные потери ЭЭ в трансформаторах
ΔW_"НТ" =ΔP_"НТ" ⋅τ
- Нагрузочные потери мощности в трансформаторах
ΔP_"НТ" =(S_"НОМ" ^2)/(U_"НОМ" ^2 )⋅R_"ЭТ" 
- Нагрузочные потери мощности в линиях
ΔP_"НЛ" =(S_"НОМ" ^2)/(U_"НОМ" ^2 )⋅R_"ЭЛ" 
- Время наибольших потерь
τ=k_И^2⋅k_Ф^2⋅Т
- Коэффициент формы графика нагрузки
k_Ф^2=("1+2" "k" _И)/("3" "k" _И )
- Коэффициент использования наибольшей нагрузки 
k_И=T_"НАИБ" /T
- Оптимальный коэффициент загрузки по критерию минимальных стоимости передачии ЭЭ
k_"ЗC" =√((p_Л⋅К_Л+p_Т⋅К_Т+ΔW_"ХХ" ⋅b_"ХХ" )/(ΔW_"НАГР" ⋅b_"НАГР"  ))
- Оптимальный коэффициент загрузки по критерию минимальных отностительных потерь ЭЭ
k_"ЗW" =√((ΔW_"ХХ" )/(ΔW_"НАГР"  ))
