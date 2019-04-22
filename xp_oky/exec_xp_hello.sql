' простая процедура, которая возвращает строковое значение

declare @r varchar (100)
exec xp_hello @r output
select @r
