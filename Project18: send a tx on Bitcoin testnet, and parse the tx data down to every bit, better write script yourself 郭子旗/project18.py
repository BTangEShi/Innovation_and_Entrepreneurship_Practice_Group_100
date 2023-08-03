from bit import PrivateKeyTestnet
my_key = PrivateKeyTestnet('cSKxS5jmxCHK6Cry9xxnCEveuFed62svVV3hsYFHdiEeXEmiFG6d')
print(my_key)
print(my_key.version)
print(my_key.to_wif())
print(my_key.address)
#print(my_key.balance_as('usd'))

print(my_key.create_transaction([('mjJEoUh5T8GjqcGndrXWFAWQahpHoMq8s1', 190, 'usd')]))
