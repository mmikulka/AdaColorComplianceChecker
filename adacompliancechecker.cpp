#include "adacompliancechecker.h"
#include <cmath>

ADAComplianceChecker::ADAComplianceChecker() {}

/**
     * @brief Normalizes color value
     * @param value: color value
     * @return normalized color value
     */
double ADAComplianceChecker::normalize(const int value)
{
    double returnValue = value/255.0;  // Normalize to range [0, 1]
    return returnValue <= 0.03928 ? (value / 12.92) : std::pow((value + 0.055) / 1.055, 2.4);
}

/**
     * @brief calculate Relative Luminance of RGB color
     * @param RGB color to calculate luminance over
     * @return luminance value of RGB color
     */
double ADAComplianceChecker::calculateRelativeLuminance(const QColor& color)
{
    double normalizedR = normalize(color.red());
    double normalizedG = normalize(color.green());
    double normalizedB = normalize(color.blue());
    return 0.2126 * normalizedR + 0.7152 * normalizedG + 0.0722 * normalizedB;
}

/**
     * @brief Calculate Constrast Ratio of the two Values
     * @param foreground color
     * @param Background color
     * @return
     */
double ADAComplianceChecker::CalculateConstrastRatio(const QColor &foreground,
                            const QColor &Background)
{
    double luminance1 = calculateRelativeLuminance(foreground);
    double luminance2 = calculateRelativeLuminance(Background);
    if (luminance1 < luminance2) std::swap(luminance1, luminance2);
    return (luminance1 + 0.05) / (luminance2 + 0.05);
}
