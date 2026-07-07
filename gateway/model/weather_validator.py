def validate(datagram):
    if _validate_format(datagram) == False:
        return False
    
    return True

def _validate_format(datagram):
    required = [
        "temperature",
        "humidity",
        "pressure"
    ]

    for field in required:
        if field not in datagram:
            return False

    return True