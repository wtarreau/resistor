#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct series {
	const char *name;       // NULL terminates the list
	const double tolerance; // tolerance in this series
	const double *values;   // zero-terminated list
};

const struct series e_series[] = {
	{
		.name = "E3", .tolerance = 0.4, .values = (const double[]){
			1.0, 2.2, 4.7,
			0.0
		}
	},
	{
		.name = "E6", .tolerance = 0.2, .values = (const double[]){
			1.0, 1.5, 2.2, 3.3, 4.7, 6.8,
			0.0
		}
	},
	{
		.name = "E12", .tolerance = 0.1, .values = (const double[]){
			1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2,
			0.0
		}
	},
	{
		.name = "E24", .tolerance = 0.05, .values = (const double[]){
			1.0, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8, 2.0, 2.2, 2.4, 2.7, 3.0,
			3.3, 3.6, 3.9, 4.3, 4.7, 5.1, 5.6, 6.2, 6.8, 7.5, 8.2, 9.1,
			0.0
		}
	},
	{
		.name = "E48", .tolerance = 0.02, .values = (const double[]){
			1.00, 1.05, 1.10, 1.15, 1.21, 1.27, 1.33, 1.40, 1.47, 1.54, 1.62, 1.69,
			1.78, 1.87, 1.96, 2.05, 2.15, 2.26, 2.37, 2.49, 2.61, 2.74, 2.87, 3.01,
			3.16, 3.32, 3.48, 3.65, 3.83, 4.02, 4.22, 4.42, 4.64, 4.87, 5.11, 5.36,
			5.62, 5.90, 6.19, 6.49, 6.81, 7.15, 7.50, 7.87, 8.25, 8.66, 9.09, 9.53,
			0.00
		}
	},
	{
		.name = "E96", .tolerance = 0.01, .values = (const double[]){
			1.00, 1.02, 1.05, 1.07, 1.10, 1.13, 1.15, 1.18, 1.21, 1.24, 1.27, 1.30,
			1.33, 1.37, 1.40, 1.43, 1.47, 1.50, 1.54, 1.58, 1.62, 1.65, 1.69, 1.74,
			1.78, 1.82, 1.87, 1.91, 1.96, 2.00, 2.05, 2.10, 2.15, 2.21, 2.26, 2.32,
			2.37, 2.43, 2.49, 2.55, 2.61, 2.67, 2.74, 2.80, 2.87, 2.94, 3.01, 3.09,
			3.16, 3.24, 3.32, 3.40, 3.48, 3.57, 3.65, 3.74, 3.83, 3.92, 4.02, 4.12,
			4.22, 4.32, 4.42, 4.53, 4.64, 4.75, 4.87, 4.99, 5.11, 5.23, 5.36, 5.49,
			5.62, 5.76, 5.90, 6.04, 6.19, 6.34, 6.49, 6.65, 6.81, 6.98, 7.15, 7.32,
			7.50, 7.68, 7.87, 8.06, 8.25, 8.45, 8.66, 8.87, 9.09, 9.31, 9.53, 9.76,
			0.00
		}
	},
	{
		.name = "E192", .tolerance = 0.005, .values = (const double[]){
			1.00, 1.01, 1.02, 1.04, 1.05, 1.06, 1.07, 1.09, 1.10, 1.11, 1.13, 1.14,
			1.15, 1.17, 1.18, 1.20, 1.21, 1.23, 1.24, 1.26, 1.27, 1.29, 1.30, 1.32,
			1.33, 1.35, 1.37, 1.38, 1.40, 1.42, 1.43, 1.45, 1.47, 1.49, 1.50, 1.52,
			1.54, 1.56, 1.58, 1.60, 1.62, 1.64, 1.65, 1.67, 1.69, 1.72, 1.74, 1.76,
			1.78, 1.80, 1.82, 1.84, 1.87, 1.89, 1.91, 1.93, 1.96, 1.98, 2.00, 2.03,
			2.05, 2.08, 2.10, 2.13, 2.15, 2.18, 2.21, 2.23, 2.26, 2.29, 2.32, 2.34,
			2.37, 2.40, 2.43, 2.46, 2.49, 2.52, 2.55, 2.58, 2.61, 2.64, 2.67, 2.71,
			2.74, 2.77, 2.80, 2.84, 2.87, 2.91, 2.94, 2.98, 3.01, 3.05, 3.09, 3.12,
			3.16, 3.20, 3.24, 3.28, 3.32, 3.36, 3.40, 3.44, 3.48, 3.52, 3.57, 3.61,
			3.65, 3.70, 3.74, 3.79, 3.83, 3.88, 3.92, 3.97, 4.02, 4.07, 4.12, 4.17,
			4.22, 4.27, 4.32, 4.37, 4.42, 4.48, 4.53, 4.59, 4.64, 4.70, 4.75, 4.81,
			4.87, 4.93, 4.99, 5.05, 5.11, 5.17, 5.23, 5.30, 5.36, 5.42, 5.49, 5.56,
			5.62, 5.69, 5.76, 5.83, 5.90, 5.97, 6.04, 6.12, 6.19, 6.26, 6.34, 6.42,
			6.49, 6.57, 6.65, 6.73, 6.81, 6.90, 6.98, 7.06, 7.15, 7.23, 7.32, 7.41,
			7.50, 7.59, 7.68, 7.77, 7.87, 7.96, 8.06, 8.16, 8.25, 8.35, 8.45, 8.56,
			8.66, 8.76, 8.87, 8.98, 9.09, 9.20, 9.31, 9.42, 9.53, 9.65, 9.76, 9.88,
			0.00
		}
	},
	{
		.name = NULL, .values = NULL
	}
};

/* display the message and exit with the code */
__attribute__((noreturn)) void die(int code, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	exit(code);
}

void help(int code, const char *cmd)
{
	die(code,
	    "Usage: %s <options>\n"
	    "  -h             show this help\n"
	    "  -d             dump all series\n"
	    "  -s <series>    use series <series> (default E24)\n"
	    "  -t <tolerance> set this tolerance (in %%) for output values (default from series)\n"
	    "  -D <target>    resolve a divider giving this ratio (uses tolerance)\n"
	    "  -P <target>    resolve a parallel couple giving this value (uses tolerance)\n"
	    "  -S <target>    resolve a series couple giving this value (uses tolerance)\n"
	    "", cmd);
}

int main(int argc, char **argv)
{
	const struct series *series = &e_series[3]; // e24
	char *cmd = argv[0];
	double tolerance = series->tolerance;

	while (argc > 1 && argv[1][0] == '-') {
		if (argv[1][1] == 'h')
			help(0, cmd);
		else if (argv[1][1] == 'd') {
			for (series = e_series; series->name; series++) {
				const double *d;

				printf("%s series:\n", series->name);
				for (d = series->values; *d; d++)
					printf("    %.2f\n", *d);
			}
			return 0;
		}
		else if (argv[1][1] == 't' && argc > 2) {
			tolerance = atof(argv[2]) / 100.0;
			argc--; argv++;
		}
		else if (argv[1][1] == 's' && argc > 2) {
			for (series = e_series;; series++) {
				if (!series->name)
					die(1, "Series %s not found. Use -d to list known ones\n", argv[2]);
				if (strcasecmp(argv[2], series->name) == 0)
					break;
			}
			tolerance = series->tolerance;
			argc--; argv++;
		}
		else if (argv[1][1] == 'D' && argc > 2) {
			/* divider resolver */
			double target = atof(argv[2]);
			const double *ru, *rd; // ratio up, down
			double pu, pd;         // power up, down
			double value;
			double error;

			for (pu = 1; pu <= 1000; pu *= 10) {
				for (ru = series->values; *ru; ru++) {
					for (pd = 1; pd <= 1000; pd *= 10) {
						for (rd = series->values; *rd; rd++) {
							value = (*rd * pd) / (*ru * pu + *rd * pd);
							error = fabs((value - target) / target);
							if (error <= tolerance) {
								printf("%.2f%% r=%.3f up=%g down=%g\n",
								       error * 100.0, value, *ru * pu, *rd * pd);
							}
						}
					}
				}
			}
			argc--; argv++;
			return 0;
		}
		else if (argv[1][1] == 'S' && argc > 2) {
			/* series resolver */
			double target = atof(argv[2]);
			const double *r1, *r2; // ratio 1,2
			double p1, p2;         // power 1,2
			double value;
			double error;

			for (p1 = 1; p1 <= 100000000; p1 *= 10) {
				for (r1 = series->values; *r1; r1++) {
					for (p2 = 1; p2 <= 100000000; p2 *= 10) {
						for (r2 = series->values; *r2; r2++) {
							value = *r1 * p1 + *r2 * p2;
							error = fabs((value - target) / target);
							if (error <= tolerance) {
								printf("%.2f%% R=%.3f R1=%.2f R2=%.2f\n",
								       error * 100.0, value, *r1 * p1, *r2 * p2);
							}
						}
					}
				}
			}
			argc--; argv++;
			return 0;
		}
		else if (argv[1][1] == 'P' && argc > 2) {
			/* parallel resolver */
			double target = atof(argv[2]);
			const double *r1, *r2; // ratio 1,2
			double p1, p2;         // power 1,2
			double value;
			double error;

			for (p1 = 1; p1 <= 100000000; p1 *= 10) {
				for (r1 = series->values; *r1; r1++) {
					for (p2 = 1; p2 <= 100000000; p2 *= 10) {
						for (r2 = series->values; *r2; r2++) {
							value = 1.0 / (1.0 / (*r1 * p1) + 1.0 / (*r2 * p2));
							error = fabs((value - target) / target);
							if (error <= tolerance) {
								printf("%.2f%% R=%.3f R1=%.2f R2=%.2f\n",
								       error * 100.0, value, *r1 * p1, *r2 * p2);
							}
						}
					}
				}
			}
			argc--; argv++;
			return 0;
		}
		else
			break;
		argc--; argv++;
	}

	help(1, cmd);
	
	return 0;
}
