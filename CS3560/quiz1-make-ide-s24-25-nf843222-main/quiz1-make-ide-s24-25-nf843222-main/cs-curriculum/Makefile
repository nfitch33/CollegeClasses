.PHONY: clean

high-school-diploma:
	@touch high-school-diploma

highSchoolDiploma:
	@touch high-school-diploma

cs2401: high-school-diploma
	@touch cs2401

cs3200: cs2401
	@touch cs3200

cs3560:
	@touch cs3560

cs3610: cs2401
	@touch cs3610

cs4000: cs3610
	@touch cs4000

cs4100: cs3200
	@touch cs4100

cs4560: cs3610
	@touch cs4560

cs4561:	cs4560
	@touch cs4561
	
undergraduate-degree: cs4561 cs4000 cs4100
	@touch undergraduate-degree

undergraduateDegree: cs4561 cs4000 cs 4100
	@touch undergraduateDegree



clean:
	-$(RM) cs* high-school-diploma undergraduate-degree
